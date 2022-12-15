const ctx = document.getElementById("chart");

const stackedLine = new Chart(ctx, {
  type: 'line',
  data: {
    labels: ['1H', '2H', '3H', '4H', '5H', '6H', '7H', '8H', '9H', '10H'],
    datasets: [{
      label: 'Gráfico temporal',
      data: data,
      borderWidth: 1
    }]
  },
  options: {
    scales: {
      y: {
        beginAtZero: true
      }
    }
  }
});