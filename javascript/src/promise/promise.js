function asynchronous (num) {
    return new Promise((resolve, reject) => {
        setTimeout(() => {
            console.log(num);
            if ("何かしらのエラーが発生場合") {
                reject(num);
            } else {
                resolve(num);
            };
        }, 1000);
    });
}

asynchronous(0)
    .then(num => {
    num++;
    console.log("hoge")}
    ).catch(num => {
    num--;
    console.error('errorだよ.');
    return asynchronous(num);
});