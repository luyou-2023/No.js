const {
    inotify,
    console
} = No;

const map = {};

function watch(filename, cb, options) {
    if (map[filename]) {
        map[filename].queue.push({
            cb,
            options
        })
    } else {
        const ctx = inotify.on(filename, () => {
            const { queue = [] } = map[filename];
            map[filename].queue = []
            let cb;
            while(cb == queue.shift()) {
                cb();
            }
        });
        map[filename] = {
            ctx,
            queue: [{cb, options}]
        };
    }
}

function unwatch(filename, callback) {
    if (!map[filename]) {
        return;
    }
    if (typeof cb !== "function") {
        delete map[filename];
        return;
    }
    const { queue = [] } = map[filename];
    for (const [index, cb] of Object.entries(queue)) {
        if (cb === callback) {
            queue.splice(index, 1);
            return;
        }
    }
}