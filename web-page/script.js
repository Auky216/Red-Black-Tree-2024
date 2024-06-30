document.addEventListener('DOMContentLoaded', () => {
    document.querySelectorAll('.fade-in').forEach(element => {
        element.style.opacity = 0;
        setTimeout(() => {
            element.style.opacity = 1;
        }, 500);
    });
});



function drawCircleChart(selector, value, maxValue, label, offsetY = 0) {
    const width = 200;
    const height = 200;
    const radius = Math.min(width, height) / 2;

    const svg = d3.select(selector)
        .attr('width', width)
        .attr('height', height)
        .append('g')
        .attr('transform', `translate(${width / 2},${height / 2 + offsetY})`);

    const color = d3.scaleOrdinal()
        .domain(['AVL', 'Red-Black'])
        .range(['steelblue', '#ff4655']);

    const pie = d3.pie()
        .value(d => d)
        .sort(null);

    const data = pie([value, maxValue - value]);

    const arc = d3.arc()
        .innerRadius(0)
        .outerRadius(radius);

    svg.selectAll('path')
        .data(data)
        .enter()
        .append('path')
        .attr('d', arc)
        .attr('fill', (d, i) => color(i))
        .attr('stroke', 'white')
        .style('stroke-width', '2px');

    svg.append('text')
        .attr('text-anchor', 'middle')
        .attr('dy', '-1.2em')
        .text(label);

    svg.append('text')
        .attr('text-anchor', 'middle')
        .attr('dy', '0.6em')
        .text(value);
}
