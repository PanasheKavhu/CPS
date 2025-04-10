const express = require('express');
const router = express.Router();
const Paynow = require('paynow');
const ParkingSlot = require('../models/ParkingSlot'); // Assuming a model for parking slots
const User = require('../models/User'); // Assuming a model for users
const Booking = require('../models/Booking'); // Assuming a model for bookings

// Paynow configuration
const paynow = new Paynow(' 20311', '2ee99cce-d8b2-432f-a075-832acc68d447');

// Endpoint to get live updates of parking slots
router.get('/slots', async (req, res) => {
    try {
        const slots = await ParkingSlot.find(); // Fetch all parking slots
        res.json(slots);
    } catch (error) {
        res.status(500).json({ message: error.message });
    }
});

// Endpoint for user login
router.post('/login', async (req, res) => {
    const { username, password } = req.body;
    try {
        const user = await User.findOne({ username });
        if (user && user.password === password) {
            res.json({ message: 'Login successful', user });
        } else {
            res.status(401).json({ message: 'Invalid credentials' });
        }
    } catch (error) {
        res.status(500).json({ message: error.message });
    }
});

// Endpoint for booking a parking slot
router.post('/book', async (req, res) => {
    const { userId, slotId } = req.body;

    try {
        // Check if the slot is available
        const slot = await ParkingSlot.findById(slotId);
        if (!slot || slot.status === 'occupied') {
            return res.status(400).json({ message: 'Slot is not available' });
        }

        // Create a new payment
        const payment = paynow.createPayment('Parking Slot Booking', 'user@example.com');
        payment.add('Parking Slot ' + slotId, 5.00); // Add item (slot booking fee)

        // Send payment to Paynow
        const response = await paynow.send(payment);

        if (response.success) {
            // Save booking details
            const booking = new Booking({ userId, slotId, paymentUrl: response.redirectUrl });
            await booking.save();

            // Respond with the payment URL
            res.json({ message: 'Booking initiated', paymentUrl: response.redirectUrl });
        } else {
            res.status(500).json({ message: 'Payment initiation failed' });
        }
    } catch (error) {
        res.status(500).json({ message: error.message });
    }
});

router.post('/paynow-notification', async (req, res) => {
    const { reference, status } = req.body;

    try {
        // Update booking status based on payment notification
        const booking = await Booking.findOne({ reference });
        if (booking) {
            booking.status = status === 'Paid' ? 'confirmed' : 'pending';
            await booking.save();
        }
        res.status(200).send('OK');
    } catch (error) {
        res.status(500).send('Error processing notification');
    }
});

module.exports = router;