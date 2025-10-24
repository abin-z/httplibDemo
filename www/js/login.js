document.getElementById('loginBtn').addEventListener('click', function() {
    const user = document.getElementById('user').value;
    const pass = document.getElementById('pass').value;

    fetch('/api/login', {
        method: 'POST',
        headers: {'Content-Type': 'application/x-www-form-urlencoded'},
        body: `user=${user}&pass=${pass}`
    })
    .then(r => {
        if (r.redirected) {
            // 登录成功重定向
            window.location = r.url;
            return;
        }
        return r.json();
    })
    .then(d => {
        if (d && !d.ok) {
            document.getElementById('msg').textContent = 'Login failed: ' + (d.msg || '');
        }
    });
});
