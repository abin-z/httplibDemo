// 加载数据接口
document.getElementById('loadDataBtn').addEventListener('click', function() {
    fetch('/api/data', { credentials: 'include' }) // 发送 cookie
      .then(r => r.json())
      .then(d => {
          if (d.error) {
              alert('Unauthorized, please login');
              window.location = '/login.html';
          } else {
              document.getElementById('output').textContent = JSON.stringify(d, null, 2);
          }
      });
});

// 登出
document.getElementById('logoutBtn').addEventListener('click', function() {
    localStorage.removeItem('token');
    window.location = '/login.html';
});
