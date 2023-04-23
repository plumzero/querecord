
#include <stdio.h>
#include <math.h>
#include <vector>
#include <map>
#include <algorithm>

// 将区间作为 map 的键，统计落入相应区间的点

const double eps = 1e-14;

struct Range {
  double left;
  double right;
  Range(double l, double r) : left(l), right(r) {}
  bool operator<(const Range& range) const {
    return left < range.left;
  }
};

struct DataSet {
  size_t cnt{0};
};

struct RangeCompare {
  double val;
  RangeCompare(double val) : val(val) {}
  bool operator()(const Range& rhs) {
    if (fabs(val - rhs.left) < eps || (val - rhs.left >= eps && rhs.right - val > eps)) {
      return true;
    }
    return false;
  }
};

int main()
{
  std::vector<Range> _vec;
  for (size_t i = 0; i < 10; i++) {
    _vec.push_back(Range(i, i + 1));
  }

  for (const auto& ele : _vec) {
    printf("left=%.0f,right=%.0f\n", ele.left, ele.right);
  }

  {
    double val = 1.2;
    auto iter = std::find_if(_vec.begin(), _vec.end(), RangeCompare(val));
    if (iter != _vec.end()) {
      printf("find %.2f at [%.0f,%.0f)\n", val, iter->left, iter->right);
    } else {
      printf("could not find %.0f\n", val);
    }
  }

  {
    double val = 2;
    auto iter = std::find_if(_vec.begin(), _vec.end(), RangeCompare(val));
    if (iter != _vec.end()) {
      printf("find %.2f at [%.0f,%.0f)\n", val, iter->left, iter->right);
    } else {
      printf("could not find %.0f\n", val);
    }
  }

  {
    double val = 10;
    auto iter = std::find_if(_vec.begin(), _vec.end(), RangeCompare(val));
    if (iter != _vec.end()) {
      printf("find %.2f at [%.0f,%.0f)\n", val, iter->left, iter->right);
    } else {
      printf("could not find %.0f\n", val);
    }
  }

  // insert to map
  std::map<Range, DataSet, std::less<Range>> _map;
  for (const auto& ele: _vec) {
    _map.insert(std::make_pair(ele, DataSet()));
  }

  {
    double val = 1;
    auto iter = std::find_if(_vec.begin(), _vec.end(), RangeCompare(val));
    if (_map.find(*iter) != _map.end()) {
      _map[*iter].cnt++;
    }

    val = 1.5;
    iter = std::find_if(_vec.begin(), _vec.end(), RangeCompare(val));
    if (_map.find(*iter) != _map.end()) {
      _map[*iter].cnt++;
    }

    val = 1.5;
    iter = std::find_if(_vec.begin(), _vec.end(), RangeCompare(val));
    if (_map.find(*iter) != _map.end()) {
      _map[*iter].cnt++;
    }

    val = 2;
    iter = std::find_if(_vec.begin(), _vec.end(), RangeCompare(val));
    if (_map.find(*iter) != _map.end()) {
      _map[*iter].cnt++;
    }

    val = 2.5;
    iter = std::find_if(_vec.begin(), _vec.end(), RangeCompare(val));
    if (_map.find(*iter) != _map.end()) {
      _map[*iter].cnt++;
    }
  }

  for (const auto& ele : _map) {
    printf("[%.0f,%.0f) = %lu\n", ele.first.left, ele.first.right, ele.second.cnt);
  }

  return 0;
}