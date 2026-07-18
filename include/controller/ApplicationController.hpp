#include "datasource/IDataSource.hpp"
#include "datasource/FakeVitalSource.hpp"
#include "model/DataModel.hpp"

class ApplicationController
{
private:
    IDataSource& source_;
    DataModel& model_;
    FakeVitalSource& vital_source_;

public:
    ApplicationController(
        IDataSource& source,
        FakeVitalSource& vital_source,
        DataModel& model);

    void UpdateECG();
    void UpdateVitals();
};