class SocietyMaintenanceExpertSystem:
    def __init__(self):
        # Initializing the facts related to the society's maintenance system
        self.water_tank_empty = False
        self.water_pump_functioning = True
        self.water_pipeline_leakage = False
        self.fuse_blown = False
        self.circuit_breaker_off = False
        self.burnt_light_bulbs = False

    def set_water_tank_status(self, status):
        self.water_tank_empty = status

    def set_water_pump_status(self, status):
        self.water_pump_functioning = status

    def set_pipeline_leakage_status(self, status):
        self.water_pipeline_leakage = status

    def set_fuse_status(self, status):
        self.fuse_blown = status

    def set_circuit_breaker_status(self, status):
        self.circuit_breaker_off = status

    def set_burnt_bulb_status(self, status):
        self.burnt_light_bulbs = status

    def check_water_supply_issue(self):
        if self.water_tank_empty:
            return "The water supply was disrupted because the water tank was empty."
        elif not self.water_pump_functioning:
            return "The water supply was disrupted because the water pump was not functioning."
        elif self.water_pipeline_leakage:
            return "The water supply was disrupted because of a leakage in the pipeline."
        else:
            return "Water supply is functioning properly."

    def check_lights_in_passage(self):
        if self.fuse_blown:
            return "The lights in the common passage were not working because the main fuse was blown."
        elif self.circuit_breaker_off:
            return "The lights in the common passage were not working because the circuit breaker was off."
        elif self.burnt_light_bulbs:
            return "The lights in the common passage were not working because the light bulbs were burnt."
        else:
            return "The lights in the common passage are functioning properly."


# Creating an instance of the expert system
maintenance_system = SocietyMaintenanceExpertSystem()

# Simulating the facts for Monday
maintenance_system.set_water_tank_status(True)  # Water tank is empty
maintenance_system.set_water_pump_status(False)  # Water pump is not working
maintenance_system.set_fuse_status(False)  # Fuse is not blown
maintenance_system.set_circuit_breaker_status(False)  # Circuit breaker is on
maintenance_system.set_burnt_bulb_status(False)  # Light bulbs are working

# Answering the queries based on simulated data
print("a) Why was there no water supply on Monday?")
print(maintenance_system.check_water_supply_issue())

print("\nb) Why were there no lights in common passage?")
print(maintenance_system.check_lights_in_passage())
