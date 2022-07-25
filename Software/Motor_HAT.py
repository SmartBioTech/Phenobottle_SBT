from PCA9685 import PCA9685

"""
One pwm generator is shared for both motor drivers on Motor HAT
"""
class Motor():
    def __init__(self, PCA8685_address, motor_index, PWM_frequency = 5):
        self.pwm = PCA9685(PCA8685_address, debug=False)
        self.pwm.setPWMFreq(PWM_frequency)

        self.motor_index = motor_index

        self.PWMA = 0
        self.AIN1 = 1
        self.AIN2 = 2
        self.PWMB = 5
        self.BIN1 = 3
        self.BIN2 = 4

        self.Dir = [
            'forward',
            'backward',
        ]

    def Run(self, direction, speed):
        if speed > 100:
            return
        if(self.motor_index == 0):
            self.pwm.setDutycycle(self.PWMA, speed)
            if(direction == self.Dir[0]):
                self.pwm.setLevel(self.AIN1, 0)
                self.pwm.setLevel(self.AIN2, 1)
            else:
                self.pwm.setLevel(self.AIN1, 1)
                self.pwm.setLevel(self.AIN2, 0)
        else:
            self.pwm.setDutycycle(self.PWMB, speed)
            if(direction == self.Dir[0]):
                self.pwm.setLevel(self.BIN1, 0)
                self.pwm.setLevel(self.BIN2, 1)
            else:
                self.pwm.setLevel(self.BIN1, 1)
                self.pwm.setLevel(self.BIN2, 0)

    def Stop(self):
        if (self.motor_index == 0):
            self.pwm.setDutycycle(self.PWMA, 0)
        else:
            self.pwm.setDutycycle(self.PWMB, 0)
