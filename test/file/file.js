const {
    fs,
    console
} = No;
const fd = fs.open('./test/file/1.txt');
const arr = new ArrayBuffer(100);
fs.readv(fd,arr , 0, (res) => {console.log(res)});
//console.log(new Uint8Array(arr));
