# eosvault
eos vault for biometric data

Problem: 

at the enterance of the hackaton , angelhack asks us to give consent to take our faces (biometric data on our face) and match that with our identity passport.
questions arises ? how i'am getting sure that my data is secure enough in angelhack servers? what if it gets leaked do i have to change my face and fingers ?
how are we going to have mass adoption of biometric identification if we don't solve the privacy and security issues related to it ?

Solution:
to solve that problem , we introduce the eosvault , a way to store in a secure manner your biometric data on the blockchain. allowing third party systems to check your identity without having to store your biometric data on thier system.


how does it work :
your biometric data is basically just a vector of nubers that represents metrics "distances" for your traits , the funny way with biometric data is you can't just hash it and store it somewhere because it's changing based on the environment you're in (light , finger pressure when taking fingerprint ...)
the idea is to store this vector with other chaff "fakes" points and locking them using your password (via a polynomial projection)

