
{
    let num = 1234;
    let formatNum = num.toLocaleString('en-US');
    console.log(formatNum);
}


{
    let num = 12345.67890;
    let formatNum = num.toLocaleString('en-US', { minimumFractionDigits: 5 });
    console.log(formatNum);
}