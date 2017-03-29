const functions = require('firebase-functions');

const admin = require('firebase-admin');
admin.initializeApp(functions.config().firebase);

exports.addDataTime = functions.database.ref('/measurement/{pushId}/value').onWrite(event => {
    const date = new Date();
    let dateFormatted = date.getDate()+":"+date.getMonth()+":"+date.getFullYear()+":"+date.getHours()+":"+date.getMinutes()+":"+date.getSeconds();

    console.log('Adding ',date,' to ',event.params.pushId, event.data.val());

    return event.data.ref.parent.child('dateTime').set(dateFormated);
});