function cocktailSort(arr) {
    const len = arr.length;
    let swapped = true;
    let start = 0;
    let end = len - 1;

    while (swapped) {
        swapped = false;

        // Od lewej do prawej (analogicznie jak w sortowaniu bąbelkowym)
        for (let i = start; i < end; i++) {
            if (arr[i] > arr[i + 1]) {
                // Zamiana miejscami
                const temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swapped = true;
            }
        }

        if (!swapped) break;

        swapped = false;
        end--;

        // Od prawej do lewej
        for (let i = end - 1; i >= start; i--) {
            if (arr[i] > arr[i + 1]) {
                // Zamiana miejscami
                const temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swapped = true;
            }
        }

        start++;
    }

    return arr;
}

module.exports = cocktailSort;