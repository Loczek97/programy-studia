const performance = require("perf_hooks").performance;

const bubbleSort = require("./algorytmy/n2/bubbleSort");
const selectionSort = require("./algorytmy/n2/selectionSort");
const dwukierunkowyBubbleSort = require("./algorytmy/n2/dwukierunkowyBubbleSort");

const mergeSort = require("./algorytmy/nlogn/mergeSort");
const quickSort = require("./algorytmy/nlogn/quickSort");
const heapSort = require("./algorytmy/nlogn/heapSort");

const wyniki_algorytmow = require("./algorytmy/wyniki_algorytmow/wyniki_algorytmow");

const n2 = [bubbleSort, selectionSort, dwukierunkowyBubbleSort];
const nazwy_n2 = ["bubbleSort", "selectionSort", "dwukierunkowyBubbleSort"];

const nlogn = [mergeSort, quickSort, heapSort];
const nazwy_nlogn = ["mergeSort", "quickSort", "heapSort"];



wyniki_algorytmow(n2, nazwy_n2);
wyniki_algorytmow(nlogn, nazwy_nlogn);