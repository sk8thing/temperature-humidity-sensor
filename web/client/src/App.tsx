import React from 'react'
import { Route, Routes, BrowserRouter } from "react-router-dom"
import { ThermometerComponent } from "./components/Thermometer"
import { PageNotFound } from "./components/PageNotFound"
import './App.css';

function App() {
  return (
    <BrowserRouter>
        <div className="container">
        <Routes>
            <Route path ="/" element={ <ThermometerComponent/> }/>
            <Route path ="*" element={ <PageNotFound/> }/>
        </Routes>
        </div>
    </BrowserRouter>
  );
}

export default App;
