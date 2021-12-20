
"use strict";

// --- 分割线 ---
{
    const wm = new WeakMap();

    class User {
        constructor(id) {
            this.idProperty = Symbol('id');
            this.setId(id);
        }

        setPrivate(property, value) {
            const privateMembers = wm.get(this) || {};
            privateMembers[property] = value;
            wm.set(this, privateMembers);
        }

        getPrivate(property) {
            return wm.get(this)[property];
        }

        setId(id) {
            this.setPrivate(this.idProperty, id);
        }

        getId() {
            return this.getPrivate(this.idProperty);
        }
    }

    const user = new User(123);
    console.log(user.getId());
    user.setId(456);
    console.log(user.getId());
}

// --- 分割线 ---
// 闭包
console.log("--- 分割线 ---");
{
    const User = (() => {
        const wm = new WeakMap();

        class User {
            constructor(id) {
                this.idProperty = Symbol('id');
                this.setId(id);
            }
    
            setPrivate(property, value) {
                const privateMembers = wm.get(this) || {};
                privateMembers[property] = value;
                wm.set(this, privateMembers);
            }
    
            getPrivate(property) {
                return wm.get(this)[property];
            }
    
            setId(id) {
                this.setPrivate(this.idProperty, id);
            }
    
            getId() {
                return this.getPrivate(this.idProperty);
            }
        }

        return User;
    }) ();

    const user = new User(123);
    console.log(user.getId());
    user.setId(456);
    console.log(user.getId());
}