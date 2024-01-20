export interface sensorToServer {
    sensorUpdate: (api_key:string, temperature: number, humidity: number) => void
}

export interface ServerToClient {
    sensorUpdate: (temperature: number, humidity: number) => void
}