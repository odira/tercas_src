#ifndef MAPPERDIALOG_H
#define MAPPERDIALOG_H

#include <vyborg.h>

class QLineEdit;


class MapperDialog : public VyborgMapperDialog
{
    Q_OBJECT


public:
    MapperDialog(QSortFilterProxyModel *proxy, QWidget *parent = 0);

protected:
    virtual void createPrivateWidgets();
    virtual void layoutPrivateWidgets();
    virtual void updatePrivateWidgets();

private:
    QLineEdit *typeLineEdit;
    QLineEdit *descriptionLineEdit;
    QLineEdit *classLineEdit;
    QLineEdit *categoryLineEdit;
    QLineEdit *WTClineEdit;
    QLineEdit *airportReferenceCodeLineEdit;
    QLineEdit *TKOFthrustLineEdit;
    QLineEdit *MTOWlineEdit;
    QLineEdit *maxEmptyWeightLineEdit;
    QLineEdit *MLWlineEdit;
    QLineEdit *maxPayloadLineEdit;
    QLineEdit *crewLineEdit;
    QLineEdit *seatsExecutiveLineEdit;
    QLineEdit *minLegroomLineEdit;
    QLineEdit *fuelCapacityLineEdit;
    QLineEdit *FLconsumptionLineEdit;
    QLineEdit *TKOFspeedLineEdit;
    QLineEdit *APPspeedLineEdit;
    QLineEdit *normalCruiseSpeedLineEdit;
    QLineEdit *maxCruiseSpeedLineEdit;
    QLineEdit *longRangeCruiseSpeedLineEdit;
    QLineEdit *landingDistanceLineEdit;
    QLineEdit *maxFLlineEdit;
    QLineEdit *maxRangeLineEdit;
    QLineEdit *rangeSeatsFullLineEdit;
    QLineEdit *wheelPlineEdit;
    QLineEdit *headWindLineEdit;
    QLineEdit *crossWindLineEdit;
    QLineEdit *tailWindLineEdit;
    QLineEdit *lengthLineEdit;
    QLineEdit *widthLineEdit;
    QLineEdit *tailHeightLineEdit;
    QLineEdit *wingspanLineEdit;
    QLineEdit *ACNlineEdit;
    QLineEdit *noteLineEdit;
    QLineEdit *wingsSquareLineEdit;
    QLineEdit *sourceLineEdit;
    QLineEdit *variableCostPerHourLineEdit;
    QLineEdit *cabinHeightLineEdit;
    QLineEdit *cabinWidthLineEdit;
    QLineEdit *cabinLengthLineEdit;
    QLineEdit *cabinVolumeLineEdit;
    QLineEdit *doorHeightLineEdit;
    QLineEdit *doorWidthLineEdit;
    QLineEdit *baggageVolIntLineEdit;
    QLineEdit *baggageVolExtLineEdit;
    QLineEdit *useableFuelLineEdit;
    QLineEdit *payloadWithFullFuelLineEdit;
    QLineEdit *BOWwithCrewLineEdit;
    QLineEdit *balancedFieldLengthLineEdit;
    QLineEdit *ROCallEnginesLineEdit;
    QLineEdit *ROConeEngineLineEdit;
    QLineEdit *enginesLineEdit;
    QLineEdit *engineModelLineEdit;
    QLineEdit *ACFTmanufactureIdLineEdit;
};

#endif // MAPPERDIALOG_H
