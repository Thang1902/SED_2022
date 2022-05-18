
// // function to check if house is suitable
// bool isSuitableHouse(House* cmphouse, Date start, Date end, string city, double rate, int points){    
//     // cout << "start date of house:" <<cmphouse->start_avai.viewDate() << endl;
//     // cout << "end date of house:" <<cmphouse->end_avai.viewDate() << endl;
//     // cout << "start required: " << start.viewDate() << endl;
//     // cout << "end required: " << end.viewDate() << endl;
//     // cout << "city: " << cmphouse->location << endl;
//     // cout << "city required: " << city << endl;
//     // cout << "After comparison: "  << end.biggerDate(cmphouse->end_avai).viewDate();
//     if (cmphouse->start_avai > start){       
//         if (end > cmphouse->end_avai){                            
//             if (city == cmphouse->location){                
//                 if (rate >= cmphouse->min_rate){
//                     if (points > (stoi(end.getDay()) - stoi(start.getDay())) * cmphouse->consuming_point){
//                         return true;
//                     }
//                 }
//             }
//         }
//     }    
//     return false;    
// }

