// This file contains the JavaScript code for the web application. 
// It handles user interactions, communicates with the server, 
// and updates the UI based on the parking slot availability.

document.addEventListener('DOMContentLoaded', function() {
    const loginForm = document.getElementById('loginForm');
    const bookingForm = document.getElementById('bookingForm');
    const parkingSlotsContainer = document.getElementById('parkingSlots');
    
    loginForm.addEventListener('submit', function(event) {
        event.preventDefault();
        const username = document.getElementById('username').value;
        const password = document.getElementById('password').value;

        fetch('/api/login', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ username, password })
        })
        .then(response => response.json())
        .then(data => {
            if (data.success) {
                alert('Login successful!');
                // Load parking slots after successful login
                loadParkingSlots();
            } else {
                alert('Login failed: ' + data.message);
            }
        });
    });

    bookingForm.addEventListener('submit', function(event) {
        event.preventDefault();
        const slotId = document.getElementById('slot').value;

        fetch('/api/book', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ slotId })
        })
        .then(response => response.json())
        .then(data => {
            if (data.paymentUrl) {
                // Redirect to Paynow payment page
                window.location.href = data.paymentUrl;
            } else {
                alert('Booking failed: ' + data.message);
            }
        });
    });

    function loadParkingSlots() {
        fetch('/api/parkingSlots')
        .then(response => response.json())
        .then(data => {
            parkingSlotsContainer.innerHTML = '';
            data.slots.forEach(slot => {
                const slotElement = document.createElement('div');
                slotElement.className = 'parking-slot';
                slotElement.innerText = `Slot ${slot.id}: ${slot.available ? 'Available' : 'Occupied'}`;
                parkingSlotsContainer.appendChild(slotElement);
            });
        });
    }
});