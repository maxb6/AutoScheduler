#ifndef VARIABLES_h
#define VARIABLES_h

//This class contains the getters and setters of the 5 variables of interest
class Variables{
	private:
		double currentTime;
		double fuelConsumption;
		double engineSpeed;
		double engineCoolantTemp;
		double currentGear;
		double vehicleSpeed;
		
	public:
		Variables(){};
	
		double getEngineCoolantTemp() const{
			return engineCoolantTemp;
		}
	
		void setEngineCoolantTemp(double egc){
			engineCoolantTemp = egc;
		}
	
		double getCurrentTime() const{
			return currentTime;
		}
	
		void setCurrentTime(double ct){
			currentTime = ct;
		}
	
		double getFuelConsumption() const{
			return fuelConsumption;
		}
	
		void setFuelConsumption(double fc){
			fuelConsumption = fc;
		}
	
		double getEngineSpeed() const{
			return engineSpeed;
		}
	
		void setEngineSpeed(double es){
			engineSpeed = es;
		}
	
		double getCurrentGear() const{
			return currentGear;
		}
	
		void setCurrentGear(double cg){
			currentGear = cg;
		}
	
		double getVehicleSpeed() const{
			return vehicleSpeed;
		}
	
		void setVehicleSpeed(double vs){
			vehicleSpeed = vs;
		}
};

#endif 