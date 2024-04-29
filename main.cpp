#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <complex>
#include <iomanip>
#include <Eigen>
#include <cstdio>
#include <random>

using namespace std;

int main() {
    // 创建 时间-磁场平面的分割,
    // 时间跨度为 0~2000, 每一份 5
    // 磁场范围 0~20, 每一份 0.1
    Eigen::SparseMatrix<int,Eigen::RowMajor> XY_Map(400, 200);


    double hzMax = 20;



    double timeStep = 1;


    for (int antNo = 0; antNo < 1; ++antNo) {

        // 单只蚂蚁
        double t = 0;
        double hz = hzMax;

        vector<int> pathX;
        vector<int> pathY;
        // vector<int> pathEmpty;

        while (hz > 0 && t < 1900) {
            {
                //Hamiltonian = Ham + hz * H_mag_Matrix;

                //K1 = -I * Hamiltonian * state;
                //K2 = -I * Hamiltonian * (state + h / 2 * K1);
                //K3 = -I * Hamiltonian * (state + h / 2 * K2);
                //K4 = -I * Hamiltonian * (state + h * K3);

                //state = state + h / 6 * (K1 + 2 * K2 + 2 * K3 + K4);

                //t += h;
            }

            // 随机选择三个 hz 点////////////////////////////////////////
            int randomMin = 2, randomMax = 3;
            random_device seed;
            ranlux48 engine(seed());
            uniform_int_distribution<> distrib(randomMin, randomMax);

            int random = distrib(engine);
            double nextHz1 = fabs(hz - pow(10, -1*random));

            random = distrib(engine);
            double nextHz2 = fabs(hz - pow(10, -1*random));

            random = distrib(engine);
            double nextHz3 = fabs(hz - pow(10, -1*random));

            ////////////////////////////////////////////////////////////////////////////////////////////////////////////
            // 三个点所在位置的分数
            // (x, y)
            // 先得到三个点的所在位置
            // PosX不能超过 400
            // PosY 不能小于 0
            int PosX = 0;
            if (t + timeStep > 2000) {
                break;
            } else {
                PosX = static_cast<int> ((t + timeStep) / 5);
            }
            int PosY1 = static_cast<int> (nextHz1 / 0.1);
            int PosY2 = static_cast<int> (nextHz2 / 0.1);
            int PosY3 = static_cast<int> (nextHz3 / 0.1);
            //int PosY = pointMax(PosX, PosY1, PosY2, PosY3, &XY_Map);
            int PosY = 0;

            vector<int> a;
            a.push_back(XY_Map.coeffRef(PosX, PosY1));
            a.push_back(XY_Map.coeffRef(PosX, PosY2));
            a.push_back(XY_Map.coeffRef(PosX, PosY3));

            int maxPoints = 0;
            int rst = 0;
            int ind = 0;
            for (ind = 0; ind < 3; ++ind) {
                if (a[ind] > maxPoints) {
                    rst = ind;
                }
            }
            if (rst == 0) {
                hz = nextHz1;
                PosY = PosY1;
            } else if (rst == 1) {
                hz = nextHz2;
                PosY = PosY2;
            } else {
                hz = nextHz3;
                PosY = PosY3;
            }

/*
            int pointMax(int PosX, int PosY1, int PosY2, int PosY3, Eigen::SparseMatrix<int, Eigen::RowMajor> * Map) {

                vector<int> a;
                a.push_back(Map->coeffRef(PosX, PosY1));
                a.push_back(Map->coeffRef(PosX, PosY2));
                a.push_back(Map->coeffRef(PosX, PosY3));

                int maxPoints = 0;
                for (auto p : a) {
                    if (p > maxPoints) {
                        maxPoints = p;
                    }
                }
                if (Map->coeffRef(PosX, PosY1) == maxPoints) {
                    return PosY1;
                } else if (Map->coeffRef(PosX, PosY2) == maxPoints) {
                    return PosY2;
                } else {
                    return PosY3;
                }
            }
            */

            // 更新 hz
            /*
            if (PosY == PosY1) {
                hz = nextHz1;
            } else if (PosY == PosY2) {
                hz = nextHz2;
            } else {
                hz = nextHz3;
            }
             */
            //cout << hz << endl;
            t += timeStep;

            // 如果下一点并没有在当前路径中, 加入到 vector 中, 否则的话忽略.

            if (pathX.empty() || (*(pathX.end()) != PosX || *(pathY.end()) != PosY)) {
                pathX.push_back(PosX);
                pathY.push_back(PosY);
            }





        }
        //cout << "?" << endl;
        // update 到 map 矩阵中

        for (int i = 0; i < pathX.size(); ++i) {
            XY_Map.coeffRef(pathX[i], pathY[i]) += 1;
        }



        // 清空当前 path
        //pathX = pathEmpty;
        //pathY = pathEmpty;
    }

    // 输出矩阵点集, 目前格式 mathematica 的 listPlot3D
    for (int i = 0; i < 400; ++i) {
        for (int j = 0; j < 200; ++j) {
            //if (XY_Map.coeffRef(i, j) != 0)
            if (XY_Map.coeffRef(i,j) != 0) {
                cout << "{" << i << ", " << j << ", " << XY_Map.coeffRef(i, j) << "}, ";
            }
        }
    }

    return 0;
}
