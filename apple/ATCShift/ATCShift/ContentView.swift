import SwiftUI


struct ContentView: View {
    var dateFormatter: DateFormatter {
        let formatter = DateFormatter()
        formatter.dateFormat = "dd MMMM yyyy"
        return formatter
    }

    let dateRange: ClosedRange<Date> = {
        let calendar = Calendar.current
        let startComponents = DateComponents(year: 1980, month: 1, day: 1)
        let endComponents = DateComponents(year: 2030, month: 12, day: 31)
        
        return
            calendar.date(from: startComponents)!
            ...
            calendar.date(from: endComponents)!
    }()

    @State private var selectedDate = Date()
    @State private var calDate = Date(timeIntervalSince1970: 0)
        
    let calendar = Calendar.current
    
    @State private var daysBetween: Int = 0
    @State private var nightShift: Int = 6
    @State private var morningShift: Int = 4
    @State private var afternoonShift: Int = 3
    @State private var eveningShift: Int = 5
    @State private var showShiftNumbers: Bool = false
    
    func calculateShifts() -> Void {
        daysBetween = Int(calendar.numberOfDaysBetween(from: selectedDate, to: calDate))
        let delta = daysBetween % 6
        
        switch delta {
        case 0:
            nightShift = 5
            morningShift = 3
            afternoonShift = 2
            eveningShift = 4
            break
        case 1:
            nightShift = 4
            morningShift = 2
            afternoonShift = 1
            eveningShift = 3
            break
        case 2:
            nightShift = 3
            morningShift = 1
            afternoonShift = 6
            eveningShift = 2
            break
        case 3:
            nightShift = 2
            morningShift = 6
            afternoonShift = 5
            eveningShift = 1
            break
        case 4:
            nightShift = 1
            morningShift = 5
            afternoonShift = 4
            eveningShift = 6
            break
        case 5:
            nightShift = 6
            morningShift = 4
            afternoonShift = 3
            eveningShift = 5
            break
        default:
            break
        }
    }
    
    
    var body: some View {
        VStack {
            Text("Shift Numbers of Date")
                .font(.largeTitle)
                .fontWeight(/*@START_MENU_TOKEN@*/.bold/*@END_MENU_TOKEN@*/)
            
            VStack {
                Text("Night shift")
                    .font(.largeTitle)
                    +
                Text("\(nightShift)")
                    .font(.largeTitle)
                    .fontWeight(.semibold)
                
                Text("Morning shift ")
                    .font(.largeTitle)
                    +
                Text("\(morningShift)")
                    .font(.largeTitle)
                    .fontWeight(.semibold)
                
                Text("Afternoon shift ")
                    .font(.largeTitle)
                    +
                Text("\(afternoonShift)")
                    .font(.largeTitle)
                    .fontWeight(.semibold)
                
                Text("Evening shift ")
                    .font(.largeTitle)
                    +
                Text("\(eveningShift)")
                    .font(.largeTitle)
                    .fontWeight(.semibold)
            }
            .frame(maxHeight: 400)
            
            DatePicker(
                "Select a date",
                selection: $selectedDate,
                in: dateRange,
                displayedComponents: .date
            )
            .datePickerStyle(GraphicalDatePickerStyle())
            .frame(minWidth: 0, maxWidth: .infinity, maxHeight: 300)
            .padding()
            
            Button(action: {
                self.calculateShifts()
            }) {
                HStack {
                    Image(systemName: "trash")
                        .font(/*@START_MENU_TOKEN@*/.title/*@END_MENU_TOKEN@*/)
                    Text("Hit me")
                        .fontWeight(.semibold)
                        .font(.title)
                }
                .frame(minWidth: 0, maxWidth: .infinity)
                .padding()
                .foregroundColor(.white)
                .background(LinearGradient(gradient: Gradient(colors: [Color.red, Color.orange]), startPoint: /*@START_MENU_TOKEN@*/.leading/*@END_MENU_TOKEN@*/, endPoint: /*@START_MENU_TOKEN@*/.trailing/*@END_MENU_TOKEN@*/))
                .cornerRadius(40)
            }
            .font(.title2)
            .padding()
        }
        .padding(.horizontal)
    }
}


#if DEBUG
struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
#endif


extension Calendar {
    func numberOfDaysBetween(from: Date, to: Date) -> Int {
        let numberOfDays = dateComponents([.day], from: from, to: to)
        var result = numberOfDays.day!
        if result < 0 {
            result = -result
        }
        return result
    }
}
