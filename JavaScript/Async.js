

function doAsyncTask(message, callback) {
    console.log(message)
    setTimeout(()=>{
        callback(message, null)
    }, 1000)
}

function asyncTaskWithCallback() {
    doAsyncTask("Hello", (result, error) => {
        if (error) {
            console.log("Error caught")
        }
        else {
            console.log("No error caught")
        }
        console.log(`Result: ${result}`)
    });
}

 
function asyncTaskWithPromise() {
    const makePromise = (...args) => {
        return new Promise((resolve, reject) => {
            // This is a not a Node styled callback. 
            // 1. data is the first argument 
            // 2. err is the second argument
            doAsyncTask(...args, (data, err) => {
                if (err) return reject(err)
                resolve(data)
            })
        })
    }
    makePromise("Hello")
        .then(result => {
            console.log(`Result: ${result}`)
        })
        .catch(error => {
            console.log("No error") 
        });
}

function asyncTaskWithAwait() {
    const makePromise = async (...args) => {
        return new Promise((resolve, reject) => {
            // This is a not a Node styled callback. 
            // 1. data is the first argument 
            // 2. err is the second argument
            doAsyncTask(...args, (data, err) => {
                if (err) return reject(err)
                resolve(data)
            })
        })
    }
    (async () => {
        let result = await makePromise("Hello")
        console.log(`Result: ${result}`)
    })()
}

// asyncTaskWithCallback()
// asyncTaskWithPromise()
asyncTaskWithAwait()