#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include<QObject>
#include<vector>

namespace FIT{
enum Place{
    Warsaw_centre,
    Warsaw_Suburbs,
    Cracov
};
enum Day{
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sundday
};

struct Event{
    std::string Title;
    Day day; //1 - poniedziałek, 7 - niedziela
    Place event_place;
    int hour;
    int minutes;
    std::string coach;
    std::vector<std::string> participants;
    Event(){
        Title="NO_TITLE";
        day=Monday;
        event_place=Warsaw_centre;
        hour = 17;
        minutes = 0;
        coach="Brak Trenera";
    }
    Event(std::string p_Title,
          Day p_day,
          Place p_place,
          std::vector<std::string> p_participants,
          int p_hour, int p_minutes,
          std::string p_coach ){
        Title=p_Title;
        day=p_day;
        event_place=p_place;
        hour = p_hour;
        minutes = p_minutes;
        participants=p_participants;
        coach=p_coach;
    }
};

}
#endif // TYPEDEFS_H
