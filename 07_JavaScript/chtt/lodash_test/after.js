
import _ from 'lodash';

var saves = ['profile', 'settings'];
 
var done = _.after(saves.length, function() {
  console.log('done saving!');
});
 
// _.forEach(saves, function(type) {
//   asyncSave({ 'type': type, 'complete': done });
// });
// => Logs 'done saving!' after the two async saves have completed.

// 
var finished = () => {
    console.log('Holy sh*t I finished it')
}
  
var code = _.after(3, finished);
code(); // ...
code(); // ...
code(); // 'Holy sh*t I finished it'
code(); // 'Holy sh*t I finished it'