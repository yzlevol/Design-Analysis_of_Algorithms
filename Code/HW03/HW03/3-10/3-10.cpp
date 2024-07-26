#include <iostream>
#include <vector>
using namespace std;
/**
 * 计算一维数组的最大子数组和
 * @param array 一维数组
 * @return 最大子数组和
 */
int max_1D(const vector<int>& array) {
    int maxSum = 0;
    int currentSum = 0;
    for (int value : array) {
        // 如果当前和小于0，则从当前元素开始重新计算
        currentSum = max(value, currentSum + value);
        // 更新最大和
        maxSum = max(maxSum, currentSum);
    }
    return maxSum;
}

/**
 * 计算二维矩阵的最大子矩阵和
 * @param matrix 二维矩阵
 * @return 最大子矩阵和
 */
int max_2D(const vector<vector<int>>& matrix) {
    int maxSum = 0;
    int rows = matrix.size();
    int cols = matrix[0].size();
    // 枚举左右边界
    for (int left = 0; left < cols; ++left) {
        vector<int> sums(rows, 0);
        // 枚举右边界
        for (int right = left; right < cols; ++right) {
            // 更新每一行的和
            for (int i = 0; i < rows; ++i) 
                sums[i] += matrix[i][right];
            // 计算并更新当前和
            int currentMax = max_1D(sums);
            maxSum = max(maxSum, currentMax);
        }
    }
    return maxSum;
}

/**
 * 计算三维长方体的最大子长方体和
 * @param cuboid 三维长方体
 * @return 最大子长方体和
 */
int max_3D(const vector<vector<vector<int>>>& cuboid) {
    int maxSum = 0;
    int depth = cuboid.size();
    int height = cuboid[0].size();
    int width = cuboid[0][0].size();
    // 枚举z轴方向
    for (int z = 0; z < depth; ++z) {
        // 枚举y轴方向
        vector<vector<int>> slices(height, vector<int>(width, 0));
        // 枚举z轴方向
        for (int x = z; x < depth; ++x) {
            // 更新每一层的和
            for (int y = 0; y < height; ++y) {
                for (int xx = 0; xx < width; ++xx) 
                    slices[y][xx] += cuboid[x][y][xx];
            }
            int currentMax = max_2D(slices);
            maxSum = max(maxSum, currentMax);
        }
    }
    return maxSum;
}

int main() {
    int m, n, p;
    cin >> m >> n >> p;
    vector<vector<vector<int>>> cuboid(m, vector<vector<int>>(n, vector<int>(p, 0)));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < p; ++k) {
                cin >> cuboid[i][j][k];
            }
        }
    }
    cout << max_3D(cuboid) << endl;
    return 0;
}