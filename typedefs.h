#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include<QObject>
#include<vector>

namespace FIT{
//enum Place{
//    Warsaw_centre,
//    Warsaw_Suburbs,
//    Cracov
//};
//enum Day{
//    Monday,
//    Tuesday,
//    Wednesday,
//    Thursday,
//    Friday,
//    Saturday,
//    Sundday
//};

struct Event{
    std::string Title;
    std::string id_zajec;
//    Day day; //1 - poniedziałek, 7 - niedziela
//    Place event_place;
    std::string date;
    std::string day;
    std::string event_place;
//    int hour;
//    int minutes;
    std::string hour;
    std::string minutes;
    std::string coach;
//    std::vector<std::string> participants;
    std::string participants;
//    int max_participants;
    std::string max_participants;
    Event(){
        Title="NO_TITLE";
        id_zajec=1;
//        day=Monday;
//        event_place=Warsaw_centre;
        date="01-01-2018";
        day="poniedzialek";
        hour = "17";
        minutes = "0";
        coach="Brak Trenera";
        participants="0";
        max_participants="15";
    }
    Event(std::string p_Title,
          std::string p_id_zajec,
//          Day p_day,
//          Place p_place,
          std::string p_date,
          std::string p_day,
          std::string p_place,
//          std::vector<std::string> p_participants,
          std::string p_participants,
//          int p_hour, int p_minutes,
          std::string p_hour,
          std::string p_minutes,
          std::string p_coach,
//          int p_max_participants
          std::string p_max_participants
          ){
        Title=p_Title;
        id_zajec=p_id_zajec;
        date=p_date;
        day=p_day;
        event_place=p_place;
        hour = p_hour;
        minutes = p_minutes;
        participants=p_participants;
        coach=p_coach;
        max_participants = p_max_participants;
    }
};

}
#endif // TYPEDEFS_H
