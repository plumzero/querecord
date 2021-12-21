
"use strict";

// 目标: 子类化 Set 同时定义一些通用函数操作
class XSet extends Set {
    union(...sets) {
        return XSet.union(this, ...sets)
    }

    intersection(...sets) {
        return XSet.intersection(this, ...sets);
    }

    difference(set) {
        return XSet.difference(this, set);
    }

    symmetricDifference(set) {
        return XSet.symmetricDifference(this, set);
    }

    cartesianProduct(set) {
        return XSet.cartesianProduct(this, set);
    }

    powserSet() {
        return XSet.powserSet(this);
    }

    // 返回两个或更多集合的并集
    static union(a, ...bSets) {
        const unionSet = new XSet(a);
        for (const b of bSets) {
            for (const bValue of b) {
                unionSet.add(bValue);
            }
        }
        return unionSet;
    }

    // 返回两个或更多集合的交集
    static intersection(a, ...bSets) {
        const intersectionSet = new XSet(a);
        for (const aValue of intersectionSet) {
            for (const b of bSets) {
                if (!b.has(aValue)) {
                    intersectionSet.delete(aValue);
                }
            }
        }
        return intersectionSet;
    }

    // 返回两个集合的差集，只存在于 a 中
    static difference(a, b) {
        const differenceSet = new XSet(a);
        for (const bValue of b) {
            if (a.has(bValue)) {
                differenceSet.delete(bValue);
            }
        }
        return differenceSet;
    }
    
    // 返回两个集合的对称差集
    static symmetricDifference(a, b) {
        return a.union(b).difference(a.intersection(b));
    }

    // 返回两个集合(数组对形式)的笛卡尔积
    // 必须返回数组集合，因为笛卡尔积可能包含相同值的对
    static cartesianProduct(a, b) {
        const cartesianProductSet = new XSet();
        for (const aValue of a) {
            for (const bValue of b) {
                cartesianProductSet.add([aValue, bValue]);
            }
        }
        return cartesianProductSet;
    }

    // 返回一个集合的幂集
    static powserSet(a) {
        const powserSet = new XSet().add(new XSet());
        for (const aValue of a) {
            for (const set of new XSet(powserSet)) {
                powserSet.add(new XSet(set).add(aValue));
            }
        }
        return powserSet;
    }
}

// 并集
{
    let xset = new XSet([1, 2, 3, 4]);
    console.log(xset);

    let outset = xset.union([2, 4, 6, 8]);
    console.log(outset);
}

// 交集
{
    let xset = new XSet([1, 2, 3, 4]);
    console.log(xset);

    let outset = xset.intersection(new Set([2, 4, 6, 8]));
    console.log(outset);
    
}