document.getElementById('loginBtn').addEventListener('click', function() {
    const user = document.getElementById('user').value;
    const pass = document.getElementById('pass').value;

    fetch('/api/login', {
        method: 'POST',
        headers: {'Content-Type': 'application/x-www-form-urlencoded'},
        body: `user=${user}&pass=${pass}`
    })
    .then(r => r.json())
    .then(d => {
        const msg = document.getElementById('msg');
        if (d.ok) {
            localStorage.setItem('token', d.token);
            window.location = '/admin.html';  // 登录成功跳转
        } else {
            msg.textContent = 'Login failed: ' + (d.msg || '');
        }
    });
});
