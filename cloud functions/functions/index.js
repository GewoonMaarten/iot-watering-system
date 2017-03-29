const functions = require('firebase-functions');

// // Start writing Firebase Functions
// // https://firebase.google.com/functions/write-firebase-functions
//
// exports.helloWorld = functions.https.onRequest((request, response) => {
//  response.send("Hello from Firebase!");
// })
exports.addDataTime = functions.database.ref('/measurement/{pushid}/value').onWrite(event => {
    const original = event.data.val();

});