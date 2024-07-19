function inicjujZgodnaTablice() {
    let tab = [];
    for (let i = 0; i < 1000; i++) {
        tab.push(i);
    }

    return tab;
}

function inicjujOdwrotnaTablice() {
    let tab = [];
    for (let i = 1000; i > 0; i--) {
        tab.push(i);
    }

    return tab;
}

function inicjujLosowaTablice() {
    let tab = [];
    for (let i = 0; i < 1000; i++) {
        tab.push(Math.floor(Math.random() * 1000));
    }

    return tab;
}


module.exports = [inicjujZgodnaTablice, inicjujOdwrotnaTablice, inicjujLosowaTablice]