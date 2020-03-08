#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#define MYSQL
#define MYSQL_DATABASE "aviation"
#define MYSQL_TABLENAME "ACFT"


enum Columns {
    ACFT_id,
    ACFT_type,
    ACFT_designator,
    ACFT_description,
    ACFT_class,
    ACFT_category,
    ACFT_WTC,
    ACFT_airportReferenceCode,
    ACFT_TKOFthrust,
    ACFT_MTOW,
    ACFT_maxEmptyWeight,
    ACFT_MLW,
    ACFT_maxPayload,
    ACFT_crew,
    ACFT_seatsExecutive,
    ACFT_minLegroom,
    ACFT_fuelCapacity,
    ACFT_FLconsumption,
    ACFT_TKOFspeed,
    ACFT_APPspeed,
    ACFT_normalCruiseSpeed,
    ACFT_maxCruiseSpeed,
    ACFT_longRangeCruiseSpeed,
    ACFT_landingDistance,
    ACFT_maxFL,
    ACFT_maxRange,
    ACFT_rangeSeatsFull,
    ACFT_wheelP,
    ACFT_headWind,
    ACFT_crossWind,
    ACFT_tailWind,
    ACFT_length,
    ACFT_width,
    ACFT_tailHeight,
    ACFT_wingspan,
    ACFT_ACN,
    ACFT_note,
    ACFT_wingsSquare,
    ACFT_source,
    ACFT_variableCostPerHour,
    ACFT_cabinHeight,
    ACFT_cabinWidth,
    ACFT_cabinLength,
    ACFT_cabinVolume,
    ACFT_doorHeight,
    ACFT_doorWidth,
    ACFT_baggageVolInt,
    ACFT_baggageVolExt,
    ACFT_useableFuel,
    ACFT_payloadWithFullFuel,
    ACFT_BOWwithCrew,
    ACFT_balancedFieldLength,
    ACFT_ROCallEngines,
    ACFT_ROConeEngine,
    ACFT_engines,
    ACFT_engineModel,
    ACFT_ACFTmanufacture_id
};


#endif // DECLARATIONS_H
