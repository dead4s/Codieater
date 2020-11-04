require('dotenv').config({ path: "../.env" });

const { spawn } = require('child_process');
const { Client } = require('pg');
const { env } = require('process');

const fs = require('fs');

const client = new Client({
    host: '127.0.0.1',
    database: env.DATABASE,
    user: env.USERNAME,
    password: env.PASSWORD,
    port: 5432,
});

// client
//   .connect()
//   .then(() => console.log('connected'))
//   .catch(err => console.error('connection error', err.stack))

client.connect();

const LANG = "CPP14";   // read from db
const CODEDIR = "1";    // mark_no
const DATADIR = "1";    // prob_no
const MEM = "";         // read from db
const TIME = "";        // read from db
const SIZE = 1024;      // read from db

const docker = spawn('docker',
    [
        'run',
        '--rm',
        '-v', '/Users/redundant4u/Documents/project/Codieater/server/src/volumes:/home/judge/volumes',
        'judge:1.0', 'sh', '-c', `./main -l ${LANG} -c ${CODEDIR} -d ${DATADIR}`
    ]);

docker.stdout.on('data', (data) => {
    const file = fs.readFileSync(`./volumes/mark_no/${CODEDIR}/result.json`);
    const json = JSON.parse(file);

    // compile complete
    if( json.compile == 1 ) {
        const length = Object.keys(json.result).length
        let score = 0;

        // 채점 결과의 msg들을 순서대로 보여주고 점수 계산
        for( let i = 0; i < length; i++ ) {
            score += json.result[i].check;
        }

        const query = {
            text: 'UPDATE history SET result = 1 WHERE mark_no = $1',
            values: [CODEDIR],
        };
    }

    // compile error
    else {
        const query = {
            text: 'UPDATE history SET result = 0 WHERE mark_no = $1',
            values: [CODEDIR],
        };
    }

    client
        .query(query)
        .then(res => console.log(res.row[0]))
        .catch(e => console.error(e.stack))

    console.log( json.compile_msg );

    // console.log(`stdout: ${data}`);
});

docker.stderr.on('data', (data) => { console.error(`stderr: ${data}`); });

docker.on('close', (code) => { console.log(`child process exited with code ${code}`); });