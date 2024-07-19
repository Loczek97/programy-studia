const fs = require("fs");
const path = require("path");
const { performance } = require("perf_hooks");
const init = require("../tablice/tablice");

const wyniki_algorytmow = (algorytmy, nazwy) => {
    try {
        const wynikiDir = path.resolve(__dirname, "../..", "__wyniki");

        if (!fs.existsSync(wynikiDir)) {
            fs.mkdirSync(wynikiDir, { recursive: true });
        }


        for (let i = 0; i < algorytmy.length; i++) {
            const func = algorytmy[i];
            const nazwa = nazwy[i];

            const filePath = path.resolve(wynikiDir, `wyniki_${nazwa}.txt`);
            const stream = fs.createWriteStream(filePath, { flags: "a" });

            for (let i = 0; i < 100; i++) {
                const wyniki = [];

                for (let j = 0; j < init.length; j++) {
                    const initFunc = init[j];

                    const array = initFunc();
                    const startTime = performance.now();
                    func(array);
                    const endTime = performance.now();
                    const executionTime = (endTime - startTime).toFixed(4);

                    wyniki.push(executionTime);
                }
                stream.write(wyniki.join(" ") + "\n");
            }

            stream.end();
        }

        return true;
    } catch (error) {
        console.error("Error in wyniki_algorytmow:", error);
        return false;
    }
};

module.exports = wyniki_algorytmow;
