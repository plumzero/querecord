
import moment from 'moment';

// npm install moment --save

function main() {
    let past = moment(new Date(2010, 1, 14, 15, 25, 50, 125), moment.ISO_8601).format('YYYY-MM-DD HH:mm:ss');
    console.log("%s", past);

    let now = moment(new Date(), moment.ISO_8601).format('YYYY-MM-DD HH:mm:ss');
    console.log("%s", now);
}

main();
