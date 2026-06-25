#include "datasource/IDataSource.hpp"
#include "datasource/FakeVitalSource.hpp"
#include "model/DataModel.hpp"

class ApplicationController
{
private:
    IDataSource& source_;
    FakeVitalSource& vital_source_;
    DataModel& model_;
    

public:
    ApplicationController(
        IDataSource& source,
        FakeVitalSource& vital_source,
        DataModel& model);

    void Update();
};