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
    @State private var morningShift: Int = 4
    @State private var daylightShift: Int = 3
    @State private var nightShift: Int = 5
    @State private var showShiftNumbers: Bool = false
    
    
    var body: some View {
        VStack {
            Text("Shift Numbers of Date")
                .fontWeight(/*@START_MENU_TOKEN@*/.bold/*@END_MENU_TOKEN@*/)
                .font(.title)
            
            VStack {
                Text("Morning shift ")
                    +
                Text("\(morningShift)")
                    .fontWeight(.semibold)
                
                Text("Daylight shift ")
                    +
                Text("\(daylightShift)")
                    .fontWeight(.semibold)
                
                Text("Night shift ")
                    +
                Text("\(nightShift)")
                    .fontWeight(.semibold)
            }
            .frame(maxHeight: 400)
            
            DatePicker(
                "Select a date",
                selection: $selectedDate,
                in: dateRange,
                displayedComponents: .date
            )
            .frame(minWidth: 0, maxWidth: .infinity, maxHeight: 200)
            .padding()
            
            Button(action: {
                daysBetween = Int(calendar.numberOfDaysBetween(from: selectedDate, to: calDate))
                morningShift = daysBetween % 6
                if morningShift == -4 {
                    morningShift = 5
                    daylightShift = 4
                    nightShift = 6
                }
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
        return numberOfDays.day!
    }
}
