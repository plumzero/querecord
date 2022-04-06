
// {
//     let p = Promise.reject(3);

//     setTimeout(console.log, 0, p);  // Promise <rejected>: 3
    
//     p.then(null, (e) => setTimeout(console.log, 0, e))
//      .catch(err => console.error('===>', err));
// }

{
    let p = Promise.reject(3);

    setTimeout(console.log, 0, p);  // Promise <rejected>: 3
    
    p.then((e) => setTimeout(console.log, 0, e))
     .catch(err => console.error('===>', err));
}