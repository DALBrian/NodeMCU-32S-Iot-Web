fetch('/data')
  .then(response => response.json())
  .then(data => {
    const timestamps = data.map(row => new Date(row[0]).toLocaleTimeString());
    const temperatures = data.map(row => row[1]);
    const humidities = data.map(row => row[2]);

    const ctx = document.getElementById('myChart').getContext('2d');
    new Chart(ctx, {
      type: 'line',
      data: {
        labels: timestamps,
        datasets: [
          {
            label: 'Temperature (°C)',
            data: temperatures,
            borderWidth: 1
          },
          {
            label: 'Humidity (%)',
            data: humidities,
            borderWidth: 1
          }
        ]
      },
      options: {
        responsive: true,
        scales: {
          y: {
            beginAtZero: false
          }
        }
      }
    });
  });