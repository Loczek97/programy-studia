function selectionSort(arr) {
    const len = arr.length;

    for (let i = 0; i < len - 1; i++) {
        let minIndex = i;

        for (let j = i + 1; j < len; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        if (minIndex !== i) {
            // Zamiana miejscami
            const temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }

    return arr;
}

module.exports = selectionSort;