export interface ServerToClient {
    sensorUpdate: (temperature: number, humidity: number) => void
}