function asynchronous (callback, num){
    setTimeout(() => {
        console.log(num);
        callback(num)
    },1000);
}

asynchronous(num => {
    num++;
    asynchronous(num =>{
        num ++;
        asynchronous(num => {
            num ++;
        }, num)
    },num)
},0)

