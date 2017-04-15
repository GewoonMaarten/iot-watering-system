const admin = require('firebase-admin');
const functions = require('firebase-functions');
const moment = require('moment-timezone');

admin.initializeApp(functions.config().firebase);


const wateringSystem = 'watering-system-0';

exports.addDateTime = functions.database.ref('/devices/1/watering-system-0/measurements/{pushId}/value').onWrite(event => {
    // Don't execute when there is no data
    data = event.data;
    if(data == undefined || !data.val()){return;}
    if (event.data.resourceState === 'not_exists') {return;}

    // Get time in Amsterdam
    const date = moment().tz("Europe/Amsterdam").format('YYYY-MM-DD HH:mm:ss');

    console.log('Adding ',date,' to ',event.params.pushId, data.val());

    return event.data.ref.parent.child('dateTime').set(date);
});

exports.cleanDatabase = functions.database.ref('/devices/1/watering-system-0/measurements').onWrite(event => {
    // Don't execute when there is no data
    data = event.data;
    if(data == undefined || !data.val()){return;}

    const oneMonthPast = moment().subtract(1, "months");
    const measurements = event.data.val();
    const keys = Object.keys(measurements);

    for(let i = 0; i < keys.length; i++) {
        let key = keys[i];
        date = measurements[key].dateTime.replace(" ", "T");
        
        if (oneMonthPast.isAfter(date)) {
            console.warn("removing: \nkey: \n", key, "\n");
            return event.data.ref.child(key).remove();
        }
    }
});