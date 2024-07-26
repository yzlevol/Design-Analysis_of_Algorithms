#include <iostream>
#include <vector>
using namespace std;
/**
 * ����һά���������������
 * @param array һά����
 * @return ����������
 */
int max_1D(const vector<int>& array) {
    int maxSum = 0;
    int currentSum = 0;
    for (int value : array) {
        // �����ǰ��С��0����ӵ�ǰԪ�ؿ�ʼ���¼���
        currentSum = max(value, currentSum + value);
        // ��������
        maxSum = max(maxSum, currentSum);
    }
    return maxSum;
}

/**
 * �����ά���������Ӿ����
 * @param matrix ��ά����
 * @return ����Ӿ����
 */
int max_2D(const vector<vector<int>>& matrix) {
    int maxSum = 0;
    int rows = matrix.size();
    int cols = matrix[0].size();
    // ö�����ұ߽�
    for (int left = 0; left < cols; ++left) {
        vector<int> sums(rows, 0);
        // ö���ұ߽�
        for (int right = left; right < cols; ++right) {
            // ����ÿһ�еĺ�
            for (int i = 0; i < rows; ++i) 
                sums[i] += matrix[i][right];
            // ���㲢���µ�ǰ��
            int currentMax = max_1D(sums);
            maxSum = max(maxSum, currentMax);
        }
    }
    return maxSum;
}

/**
 * ������ά�����������ӳ������
 * @param cuboid ��ά������
 * @return ����ӳ������
 */
int max_3D(const vector<vector<vector<int>>>& cuboid) {
    int maxSum = 0;
    int depth = cuboid.size();
    int height = cuboid[0].size();
    int width = cuboid[0][0].size();
    // ö��z�᷽��
    for (int z = 0; z < depth; ++z) {
        // ö��y�᷽��
        vector<vector<int>> slices(height, vector<int>(width, 0));
        // ö��z�᷽��
        for (int x = z; x < depth; ++x) {
            // ����ÿһ��ĺ�
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