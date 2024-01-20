import {ComponentPreview, Previews} from "@react-buddy/ide-toolbox";
import {PaletteTree} from "./palette";
import App from "../App";
import {ThermometerComponent} from "../components/Thermometer";

const ComponentPreviews = () => {
    return (
        <Previews palette={<PaletteTree/>}>
            <ComponentPreview path="/App">
                <App/>
            </ComponentPreview>
            <ComponentPreview path="/ThermometerComponent">
                <ThermometerComponent/>
            </ComponentPreview>
        </Previews>
    );
};

export default ComponentPreviews;