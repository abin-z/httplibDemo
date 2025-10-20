// 加载数据接口
document.getElementById('loadDataBtn').addEventListener('click', function() {
    const token = localStorage.getItem('token');
    if (!token) {
        alert('Please login');
        window.location = '/login.html';
        return;
    }

    fetch('/api/data', { headers: {'Authorization': token} })
      .then(r => r.json())
      .then(d => {
          if (d.error) {
              alert('Login required');
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
