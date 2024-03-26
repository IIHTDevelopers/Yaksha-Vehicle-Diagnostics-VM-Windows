#include <iostream>
#include <vector>
#include <memory>
#include <string>

using namespace std;

class Faults {
  public: enum ecuType {
    Engine,
    Transmission,
    Brake
  };
  short maxNo;
  string strFaultDescription;
  virtual void clearFaultCodes() = 0;
  virtual string getFaultDescription() = 0;
  virtual~Faults() {};
  virtual void setRandomError() = 0;

  Faults() {
    maxNo = 4;
  }
};

class EngineFaults: public Faults {
  public: enum class faultType {
    overheating,
    leakingCoolant,
    oxygenSensorError,
    poorCompression,
    noError
  };
  faultType faultInEngine = faultType::noError;

  void clearFaultCodes() override {
    faultInEngine = faultType::noError;
    cout << "Engine fault code is cleared.\n";
  }

  void setRandomError() override {
    int randomError = rand() % maxNo;
    switch (randomError) {
    case 0:
      faultInEngine = faultType::overheating;
      break;
    case 1:
      faultInEngine = faultType::leakingCoolant;
      break;
    case 2:
      faultInEngine = faultType::oxygenSensorError;
      break;
    case 3:
      faultInEngine = faultType::poorCompression;
      break;
    }
  }

  string getFaultDescription() override {
    setRandomError();
    if (faultInEngine == faultType::overheating) {
      strFaultDescription = "E001: Engine is over heated.";
    } else if (faultInEngine == faultType::leakingCoolant) {
      strFaultDescription = "E002: Engine coolant is leaking.";
    } else if (faultInEngine == faultType::oxygenSensorError) {
      strFaultDescription = "E003: Engine is not sensing oxygen properly.";
    } else if (faultInEngine == faultType::poorCompression) {
      strFaultDescription = "E004: Engine compression is poor.";
    } else {
      strFaultDescription = "Engine is not having any fault.";
    }

    return strFaultDescription;
  }
};

class TransmissionFaults: public Faults {
  public: enum class faultType {
    slipping,
    excessiveNoise,
    leakingSeals,
    completeFailure,
    noError
  };
  faultType faultInTransmission = faultType::noError;

  void clearFaultCodes() override {
    faultInTransmission = faultType::noError;
    cout << "Transmission fault code is cleared.\n";
  }

  void setRandomError() override {
    int randomError = rand() % maxNo;
    switch (randomError) {
    case 0:
      faultInTransmission = faultType::slipping;
      break;
    case 1:
      faultInTransmission = faultType::excessiveNoise;
      break;
    case 2:
      faultInTransmission = faultType::leakingSeals;
      break;
    case 3:
      faultInTransmission = faultType::completeFailure;
      break;
    }
  }

  string getFaultDescription() override {
    setRandomError();
    if (faultInTransmission == faultType::slipping) {
      strFaultDescription = "T001: There is slipping error.";
    } else if (faultInTransmission == faultType::excessiveNoise) {
      strFaultDescription = "T002: There is excessive noise.";
    } else if (faultInTransmission == faultType::leakingSeals) {
      strFaultDescription = "T003: The seal is leaking.";
    } else if (faultInTransmission == faultType::completeFailure) {
      strFaultDescription = "T004: There is complete transmission failure.";
    } else {
      strFaultDescription = "Transmission is not having any fault.";
    }

    return strFaultDescription;
  }
};

class BrakeFaults: public Faults {
  public: enum class faultType {
    squeakingNoise,
    linesLeak,
    leakingSeals,
    completeFailure,
    noError
  };
  faultType faultInBrake = faultType::noError;

  void clearFaultCodes() override {
    faultInBrake = faultType::noError;
    cout << "Break fault code is cleared.\n";
  }

  void setRandomError() override {
    int randomError = rand() % maxNo;
    switch (randomError) {
    case 0:
      faultInBrake = faultType::squeakingNoise;
      break;
    case 1:
      faultInBrake = faultType::linesLeak;
      break;
    case 2:
      faultInBrake = faultType::leakingSeals;
      break;
    case 3:
      faultInBrake = faultType::completeFailure;
      break;
    }
  }

  string getFaultDescription() override {
    setRandomError();
    if (faultInBrake == faultType::squeakingNoise) {
      strFaultDescription = "B001: There is squeaking noise while braking.";
    } else if (faultInBrake == faultType::linesLeak) {
      strFaultDescription = "B002: There is leak in the brake lines.";
    } else if (faultInBrake == faultType::leakingSeals) {
      strFaultDescription = "B003: The seal is leaking.";
    } else if (faultInBrake == faultType::completeFailure) {
      strFaultDescription = "B004: There is complete brake failure.";
    } else {
      strFaultDescription = "Brake is not having any fault.";
    }

    return strFaultDescription;
  }
};

// Abstract ECU class
class ECU {
  string strEcuName;
  public:
    Faults * faults = NULL;

  void clearFaultCodes() {
    faults -> clearFaultCodes();
  }

  void setEcuName(string strEcuName) {
    this -> strEcuName = strEcuName;
  }
  string getEcuName() {
    return this -> strEcuName;
  }

  virtual void simulateFault() = 0;
  virtual std::string getFaultCode() const = 0;
  virtual~ECU() {}
};

// Derived classes for specific ECUs
class EngineControlUnit: public ECU {
  public:

    EngineControlUnit() {
      setEcuName("EngineECU");
      faults = new EngineFaults();
    }
    ~EngineControlUnit() {
      delete faults;
    }

  void simulateFault() override {
    std::cout << "Engine fault simulated.\n";
  }
  std::string getFaultCode() const override {
    string strEngineFault = faults -> getFaultDescription();
    return strEngineFault;
  }
};

class TransmissionControlUnit: public ECU {
  public: TransmissionControlUnit() {
      setEcuName("TransmissionEcu");
      faults = new TransmissionFaults();
    }
    ~TransmissionControlUnit() {
      delete faults;
    }

  void simulateFault() override {
    std::cout << "Transmission fault simulated.\n";
  }
  std::string getFaultCode() const override {
    string strTransmissionFault = faults -> getFaultDescription();
    return strTransmissionFault;
  }
};

class BrakeControlUnit: public ECU {
  public: BrakeControlUnit() {
      setEcuName("BrakeEcu");
      faults = new BrakeFaults();
    }
    ~BrakeControlUnit() {
      delete faults;
    }

  void simulateFault() override {
    std::cout << "Brake fault simulated.\n";
  }
  std::string getFaultCode() const override {
    string strBrakeFault = faults -> getFaultDescription();
    return strBrakeFault;
  }
};

class User {
  string userName;
  public:
    void setName(string userName) {
      this -> userName = userName;
    }

  void sendMessage(string vehicleName, string vehicleFaultDescription) {
    cout << "The faults detected in vehicle named: " << vehicleName << " are:\n";
    cout << vehicleFaultDescription;
    cout << endl;
    cout << "Details are send to user: " << userName << "." << endl;
  }
};

// Vehicle class
class Vehicle {
  std::vector < std::unique_ptr < ECU >> ecus;
  string name;
  string strFaultDesription;
  User user;
  public:
    void setName(string name) {
      this -> name = name;

    }
  string getName() {
    return this -> name;
  }

  void setFaultDesription(string strFaultDesription) {
    this -> strFaultDesription = strFaultDesription;

  }
  string getFaultDesriptione() {
    return this -> strFaultDesription;
  }

  void addECU(std::unique_ptr < ECU > ecu) {
    ecus.push_back(std::move(ecu));
  }

  const std::vector < std::unique_ptr < ECU >> & getECUs() const {
    return ecus;
  }

  void getEcuNames() {
    for (const auto & ecu: ecus) {
      cout << ecu -> getEcuName() << " ";
    }
    cout << "\n";
  }

  void addUser(User user) {
    this -> user = user;
  }

  void clearFaultCodes() {
    vector < std::unique_ptr < ECU >> ::iterator iter = ecus.begin();
    for (iter; iter < ecus.end(); iter++) {
      ( * iter) -> clearFaultCodes();
    }
  }

  void sendMessageToUser(string diagnosticDescription) {
    user.sendMessage(name, diagnosticDescription);
  }

};

// DiagnosticTool class
class DiagnosticTool {
  string diagnosticDescription;
  public:
    void diagnose(const Vehicle & vehicle) {
      diagnosticDescription = "";
      const auto & ecus = vehicle.getECUs();
      for (const auto & ecu: ecus) {
        ecu -> simulateFault();
        string faultDetected = ecu -> getFaultCode();
        diagnosticDescription += faultDetected;
        std::cout << faultDetected << std::endl;
      }
    }

  string GetDiagnosticDescription() {
    return diagnosticDescription;
  }
  void SetDiagnosticDescription(string diagnosticDescription) {
    this -> diagnosticDescription = diagnosticDescription;
  }
};

int main() {
  int userInput;
  Vehicle vehicle;
  vehicle.addECU(std::make_unique < EngineControlUnit > ());
  vehicle.addECU(std::make_unique < TransmissionControlUnit > ());
  vehicle.addECU(std::make_unique < BrakeControlUnit > ());
  string strVehicleName;
  User user;
  string userName;
  DiagnosticTool tool;
  string diagnosticDescription;

  do {
    cout << "Automotive Diagnostic System Simulator:\n";
    cout << " 0. Quit.\n";
    cout << " 1. Add vehicle.\n";
    cout << " 2. View all ECUs.\n";
    cout << " 3. Simulating Faults.\n";
    cout << " 4. Clear fault codes.\n";
    cout << " 5. Send fault details to user via message and email.\n";
    cout << "Enter your choice: ";
    cin >> userInput;

    switch (userInput) {
    case 0:
      cout << "Exiting program.\n";
      break;
    case 1:
      cout << "Enter the vehicle name: \n";
      cin >> strVehicleName;
      vehicle.setName(strVehicleName);
      break;
    case 2:
      if (strVehicleName == "") {
        cout << "No vehicle details are there. Please add vehicle." << endl;
        continue;
      }
      vehicle.getEcuNames();
      break;
    case 3:
      if (strVehicleName == "") {
        cout << "No vehicle details are there. Please add vehicle." << endl;
        continue;
      }
      tool.diagnose(vehicle);
      diagnosticDescription = tool.GetDiagnosticDescription();
      break;
    case 4:
      if (strVehicleName == "") {
        cout << "No vehicle details are there. Please add vehicle." << endl;
        continue;
      }
      if (diagnosticDescription == "") {
        cout << "No diagnostic operation is performed" << endl;
        continue;
      }
      vehicle.clearFaultCodes();
      vehicle.setName(strVehicleName);
      tool.SetDiagnosticDescription("");
      break;
    case 5:
      if (strVehicleName == "") {
        cout << "No vehicle details are there. Please add vehicle." << endl;
        continue;
      }
      diagnosticDescription = tool.GetDiagnosticDescription();
      if (diagnosticDescription == "") {
        cout << "No diagnostic operation is performed" << endl;
        continue;
      }
      cout << "Enter user name: \n";
      cin >> userName;
      user.setName(userName);
      vehicle.addUser(user);
      vehicle.sendMessageToUser(diagnosticDescription);
      break;
    default:
      cout << "Invalid choice. Please try again.\n";
    }
  } while (userInput != 0);

  return 0;
}
