const functions = require('firebase-functions');
const dateTime = require('date-time');

const admin = require('firebase-admin');
admin.initializeApp(functions.config().firebase);

exports.addDateTime = functions.database.ref('/measurement/{pushId}/value').onWrite(event => {
    const date = dateTime();

    console.log('Adding ',date,' to ',event.params.pushId, event.data.val());

    return event.data.ref.parent.child('dateTime').set(date);
});