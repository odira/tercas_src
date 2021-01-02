import SwiftUI

struct ShiftRow: View {
    var title: String
    var shift: Int
    
    var body: some View {
        HStack {
            Image("icon")
                .resizable()
                .frame(width: 50, height: 50)
            VStack(alignment: .leading) {
                Text(title)
                    .font(.title2)
                Text("From 0 to 10")
                    .font(.subheadline)
                    .foregroundColor(.secondary)
            }
            Spacer()
            Text(String(shift))
                    .font(.title)
        }
    }
}

struct ShiftRow_Previews: PreviewProvider {
    static var previews: some View {
        Group {
            ShiftRow(title: "Evening", shift: 4)
        }
        .previewLayout(.fixed(width: 300, height: 70))
    }
}
