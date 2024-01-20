import React from "react"
import { ThermometerState } from "../interfaces/Thermometer"
import { io, Socket } from "socket.io-client"
import Thermometer from "react-thermometer-component"
import { ServerToClient } from "../interfaces/Events"

export class ThermometerComponent extends React.Component<any, ThermometerState> {
    private socket!: Socket<ServerToClient>;
    constructor(props: any) {
        super(props);
        this.state = {
            temperature: 0,
            humidity: 0
        }
    }

    componentDidMount() {
        this.socket = io("https://example.com")

        this.socket.on("sensorUpdate", (temperature, humidity) => {
            this.setState({
                temperature: temperature,
                humidity: humidity
            })
        })
    }

    componentWillUnmount() {
        this.socket.close()
    }

    render() {
        return(
            <div className="thermometer-container">
                <div className="icon">
                    <Thermometer
                        theme={"dark"}
                        reverseGradient={true}
                        format={"°C"}
                        steps={1}
                        max={40}
                        value={this.state.temperature}
                    />
                </div>
                <div className="data-container">
                    <div className="element">
                        <div className="text">
                            Temperature
                        </div>
                        <div className="temperature">
                            {this.state.temperature}°C
                        </div>
                    </div>
                    <div className="element">
                        <div className="text">
                            Humidity
                        </div>
                        <div className="humidity">
                            {this.state.humidity}%
                        </div>
                    </div>
                </div>
            </div>
        )
    }
}