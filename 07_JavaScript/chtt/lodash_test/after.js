
import _ from 'lodash';

var steps = [ 'profile', 'settings', 'working', 'finished' ];
 
var skip = _.after(steps.length, function() {
    console.log('dont print this!');
});

console.log('第一次测试:');
for (let step of steps) {
    if (step === 'settings') {
        console.log('skip:', step);
        continue;                   // 跳过，就不完整了，不再打印
    }
    console.log('step:', step);

    skip();
}

var done = _.after(steps.length, function() {
    console.log('would print this!');
});
  
console.log('第二次测试:');
for (let step of steps) {
    console.log('step:', step);
    done();
}

var more = _.after(steps.length, function() {
    console.log('would print this 3 times!');
});
  
console.log('第三次测试:');
for (let i = 0; i < steps.length + 2; i++) {
    console.log('step:', steps[i]);
    more();
}

var done = _.after(steps.length, function() {
    console.log('would print this!');
});
  
console.log('第四次测试:');
for (let step of steps) {
    console.log('step:', step);
    if (step === 'settings' || step === 'finished') {
        done();
    } else {
        done();
    }
}