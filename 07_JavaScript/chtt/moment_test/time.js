
import moment from 'moment';

// npm install moment --save

function main() {
    // unix 时间戳(毫秒)转特定时间格式
    console.log("unix 时间戳(毫秒)转特定时间格式");
    let unix_stamp_milliseconds = 1642643452000.345;
    let clock_time = moment(moment(Number(unix_stamp_milliseconds)).toDate().toISOString(), moment.ISO_8601).format('HHmmssSSS');
    console.log(clock_time);

    // unix 时间戳(毫秒)转特定时间格式
    console.log("unix 时间戳(毫秒)转特定时间格式");
    let now = moment.now();
    console.log(now);
    let now_time = moment(moment(Number(now)).toDate().toISOString(), moment.ISO_8601).format('HHmmssSSS');
    console.log(now_time);

    // utc 时间
    console.log("utc 时间");
    let utc = moment.utc().toISOString();
    console.log(utc);
    let utc_fmt = moment.utc().format('YYYY-DD-MM HH:mm:ss');
    console.log(utc_fmt);

    // 加减时间
    console.log("加减时间");
    let anchor = moment.utc('2015-05-05T12:00:00', moment.ISO_8601);
    let before = anchor.clone().subtract(1, 'days');
    let after = anchor.clone().add(3, 'hours');
    console.log(anchor.toISOString());
    console.log(before.toISOString());
    console.log(after.toISOString());
}

main();
